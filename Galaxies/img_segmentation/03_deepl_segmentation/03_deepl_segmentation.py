import torch
import torchvision
from PIL import Image # Pillow (Fork of the Python Imaging Library)
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Patch

# Datacheck imports
from torchvision.models.segmentation import DeepLabV3
from torchvision.transforms import Compose
from torch import Tensor
from numpy import float64

if __name__ == "__main__":
    RGB:    str = "RGB"
    CUDA:   str = "cuda"
    UINT_8: str = "uint8"
    REPO_RELATIVE_PATH: str = "Galaxies/img_segmentation/03_deepl_segmentation/"
    INPUT_IMG_NAME: str = "merged.jpg"

    print("Loading the DeepLabV3 pre-trained model...")
    model: DeepLabV3 = torchvision.models.segmentation.deeplabv3_resnet101(weights="DEFAULT")
    model.eval()
    print("Model was successfully loaded!")

    # COCO (Common Objects in Context) dataset class names.
    # DeepLabV3 was trained on PASCAL VOC, which has 21 classes (20 objects + background).
    COCO_INSTANCE_CATEGORY_NAMES = [
        "__background__", "aeroplane", "bicycle", "bird", "boat", "bottle", "bus",
        "car", "cat", "chair", "cow", "diningtable", "dog", "horse", "motorbike",
        "person", "pottedplant", "sheep", "sofa", "train", "tvmonitor"
    ]

    # Load input image.
    input_image: Image = None
    try:
        input_image = Image.open(REPO_RELATIVE_PATH+f"content/{INPUT_IMG_NAME}").convert(RGB)
    except Exception:
        print("Error while loading image!")
        raise
    input_image = input_image.resize((400, 250))

    # Converts image from PIL object to a PyTorch Tensor.
    # The Compose function chains multiple transforms together.
    pre_process: Compose = Compose([
        # ToTensor() converts PIL Image (H x W x C) with values [0, 255]
        # to a Tensor (C x H x W) with values [0.0, 1.0]
        torchvision.transforms.ToTensor(),
        # Normalize using ImageNet dataset statistics (mean and std for RGB channels).
        # These specific values are standard for models pre-trained on ImageNet,
        # ensuring the input distribution matches what the model expects.
        torchvision.transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])

    # Apply the preprocessing transforms to the input image.
    input_tensor: Tensor = pre_process(img=input_image)
    # unsqueeze(dim=0) adds a batch dimension at position 0.
    # Neural networks expect input in shape (Batch, Channels, Height, Width).
    # This converts shape from (C, H, W) to (1, C, H, W) for single image inference.
    input_batch: Tensor = input_tensor.unsqueeze(dim=0)

    print("Making prediction...")

    # If cuda is available, use it.
    if torch.cuda.is_available():
        input_batch = input_batch.to(CUDA)
        model.to(CUDA)

    # Disabling gradient calculation is useful for inference, when you are sure that you will not call Tensor.backward().
    # It will reduce memory consumption for computations that would otherwise have requires_grad=True.
    with torch.no_grad():
        # DeepLabV3 returns a dictionary with key "out" containing the segmentation map.
        # The output shape is (batch_size, num_classes, height, width).
        # We take [0] to get the first (and only) image's predictions,
        # resulting in shape (num_classes=21, height, width) - one probability map per class.
        output = model(input_batch)["out"][0]

    # argmax(0) finds the class index with highest probability for each pixel.
    # This converts from (21, H, W) probability maps to (H, W) class labels,
    # where each pixel value is 0-20 representing the predicted class.
    output_predictions = output.argmax(0)
    print("Finished preiction")

    # Convert predictions to a numpy array for visualization:
    # .byte() converts to uint8 (0-255 range), .cpu() moves from GPU to CPU,
    # .numpy() converts PyTorch tensor to NumPy array.
    mask = output_predictions.byte().cpu().numpy()

    # Creates a colors palette to open each object class. (background, plane, person, car...)
    # Uses prime-related numbers (2^25-1, 2^15-1, 2^21-1) to create visually distinct colors.
    # These specific powers create a spread of RGB values that look different from each other.
    palette: Tensor = torch.tensor([2 ** 25 - 1, 2 ** 15 -1, 2 ** 21 - 1])
    # Multiply each class index (0-20) by the palette to generate unique RGB triplets.
    # [:, None] reshapes to (21, 1) for broadcasting, resulting in shape (21, 3).
    colors: Tensor = torch.as_tensor([i for i in range(21)])[:, None] * palette
    colors = (colors % 255).numpy().astype(UINT_8)

    # Create an image from the mask array and convert to "P" (palette/indexed) mode.
    # "P" mode uses a color lookup table where each pixel value (0-20) maps to an RGB color.
    result_mask_rgb: Image = Image.fromarray(mask).convert("P")
    # Apply the custom color palette to the indexed image.
    # This maps each class index to its corresponding RGB color.
    result_mask_rgb.putpalette(colors)

    # Find all unique class IDs present in the segmentation mask.
    detected_ids: np.ndarray = np.unique(mask)

    legend_elements: list[Patch] = []
    for class_id in detected_ids:
        # Skip background class.
        if class_id == 0:
            continue
        class_name: str = COCO_INSTANCE_CATEGORY_NAMES[class_id]
        # Normalize color from [0-255] to [0.0-1.0] range (matplotlib expects floats).
        color: float64 = colors[class_id] / 255.0
        patch: Patch = Patch(facecolor=color, label=class_name)
        legend_elements.append(patch)

    _, ax = plt.subplots(figsize=(15, 10))
    ax.imshow(input_image)
    # Overlay the colored segmentation mask with 60% opacity (alpha=0.6).
    ax.imshow(result_mask_rgb, alpha=0.6)

    # Add a legend showing which colors correspond to which detected objects.
    ax.legend(handles=legend_elements, bbox_to_anchor=(1.05, 1), loc="upper left", title="Detected objects")

    ax.axis("off")
    plt.title("Segmentation with pre-trained DeepLabV3")
    plt.tight_layout()
    plt.show()
